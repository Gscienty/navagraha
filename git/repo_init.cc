#include "git/repo_init.hpp"
#include <git2/repository.h>
#include <git2/global.h>
#include <git2/remote.h>
#include <git2/config.h>
#include <git2/annotated_commit.h>
#include <git2/refs.h>
#include <git2/merge.h>
#include <git2/errors.h>
#include <git2/types.h>
#include <git2/object.h>
#include <git2/tree.h>
#include <git2/commit.h>
#include <git2/errors.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

namespace navagraha {
namespace git {


repo_init::repo_init(std::string repo_path,
                     std::string url,
                     bool local,
                     std::string template_path)
    : repo_handler(nullptr)
    , template_remote(nullptr)
    , repo_path(repo_path)
    , url(url)
    , template_path(template_path)
    , local(local)
{

}

repo_init::~repo_init()
{
    if (this->repo_handler != nullptr) {
        git_repository_free(this->repo_handler);
    }
    if (this->template_remote != nullptr) {
        git_remote_free(this->template_remote);
    }
}

void repo_init::static_construct()
{
    git_libgit2_init();
}

void repo_init::init()
{
    git_repository_init(&this->repo_handler, this->repo_path.c_str(), 0);

    this->set_template_remote();
}

void repo_init::set_template_remote()
{
    git_remote_create(&this->template_remote,
                      this->repo_handler,
                      "nava_template",
                      this->url.c_str());
}

void repo_init::perform_fastforward(const git_oid * target_oid, bool is_unborn)
{
    git_checkout_options checkout_opts;
    git_reference * target_ref = nullptr;
    git_reference * new_target_ref = nullptr;
    git_object * target = nullptr;
    git_commit * nava_comm = nullptr;
    git_tree * root_tree = nullptr;
    git_tree_entry * template_tree = nullptr;
    int err;

    git_checkout_init_options(&checkout_opts, GIT_CHECKOUT_OPTIONS_VERSION);

    if (is_unborn) {
        const char * symbolic_ref = nullptr;
        git_reference * head_ref = nullptr;

        err = git_reference_lookup(&head_ref, this->repo_handler, "HEAD");
        if (err != 0) {
            goto clean;
        }
        
        symbolic_ref = git_reference_symbolic_target(head_ref);

        err = git_reference_create(&target_ref, this->repo_handler, symbolic_ref, target_oid, 0, nullptr);
        if (err != 0) {
            goto clean;
        }

        git_reference_free(head_ref);
    }
    else {
        err = git_repository_head(&target_ref, this->repo_handler);
        if (err != 0) {
            goto clean;
        }
    }

    err = git_commit_lookup(&nava_comm, this->repo_handler, target_oid);
    if (err != 0) {
        goto clean;
    }

    err = git_commit_tree(&root_tree, nava_comm);
    if (err != 0) {
        goto clean;
    }

    err = git_tree_entry_bypath(&template_tree, root_tree, this->template_path.c_str());
    if (err != 0) {
        goto clean;
    }

    err = git_tree_entry_to_object(&target, this->repo_handler, template_tree);
    if (err != 0) {
        goto clean;
    }

    checkout_opts.checkout_strategy = GIT_CHECKOUT_SAFE;
    err = git_checkout_tree(this->repo_handler, target, &checkout_opts);
    if (err != 0) {
        goto clean;
    }
    
    err = git_reference_set_target(&new_target_ref, target_ref, target_oid, NULL);

clean:
    git_reference_free(target_ref);
    git_reference_free(new_target_ref);
    git_object_free(target);
    git_commit_free(nava_comm);
    git_tree_free(root_tree);
    git_tree_entry_free(template_tree);
}

void repo_init::merge()
{
    git_reference * ref = nullptr;
    git_annotated_commit * nava_template_comm = nullptr;
    git_merge_options merge_opts;
    git_checkout_options checkout_opts;
    git_merge_analysis_t merge_analysis;
    git_merge_preference_t merge_perference;
    git_repository_state_t state;
    const git_oid * target_oid = nullptr;

    state = static_cast<git_repository_state_t>(git_repository_state(this->repo_handler));
    if (state != GIT_REPOSITORY_STATE_NONE) {
        return;
    }

    git_merge_init_options(&merge_opts, GIT_MERGE_OPTIONS_VERSION);
    git_checkout_init_options(&checkout_opts, GIT_CHECKOUT_OPTIONS_VERSION);
    git_reference_lookup(&ref, this->repo_handler, "refs/remotes/nava_template/master");
    git_annotated_commit_from_ref(&nava_template_comm, this->repo_handler, ref);

    git_merge_analysis(&merge_analysis, &merge_perference,
                       this->repo_handler,
                       const_cast<const git_annotated_commit **>(&nava_template_comm),
                       1UL);

    if (merge_analysis & GIT_MERGE_ANALYSIS_UP_TO_DATE) {
        printf("Already up-to-date\n");
    }
    else if (merge_analysis & GIT_MERGE_ANALYSIS_UNBORN ||
             (merge_analysis & GIT_MERGE_ANALYSIS_FASTFORWARD &&
              !(merge_perference & GIT_MERGE_PREFERENCE_NO_FASTFORWARD))) {
        if (merge_analysis & GIT_MERGE_ANALYSIS_UNBORN) {
            printf("Unborn\n");
        }
        else {
            printf("Fask-Forward\n");
        }

        target_oid = git_annotated_commit_id(nava_template_comm);
        this->perform_fastforward(target_oid, merge_analysis & GIT_MERGE_ANALYSIS_UNBORN);
    }
    else if (merge_analysis & GIT_MERGE_ANALYSIS_NORMAL) {
        merge_opts.flags = static_cast<git_merge_flag_t>(0);
        merge_opts.file_flags = GIT_MERGE_FILE_STYLE_DIFF3;

        checkout_opts.checkout_strategy = GIT_CHECKOUT_FORCE | GIT_CHECKOUT_ALLOW_CONFLICTS;

        git_merge(this->repo_handler,
                  const_cast<const git_annotated_commit **>(&nava_template_comm),
                  1UL,
                  &merge_opts,
                  &checkout_opts);
    }
}

void repo_init::fetch_template()
{
    git_fetch_options fetch_opts;
    git_fetch_init_options(&fetch_opts, GIT_FETCH_OPTIONS_VERSION);

    if (this->template_remote == nullptr) {
        return;
    }

    if (this->local) {
        git_remote * local_remote = nullptr;
        git_remote_lookup(&local_remote, this->repo_handler, "nava_template");
        git_remote_fetch(local_remote, NULL, &fetch_opts, "fetch");
        printf("%d %s\n", giterr_last()->klass, giterr_last()->message);
    }
    else {
        git_remote_fetch(this->template_remote, NULL, &fetch_opts, "fetch");
        this->merge();
    }

}

}
}
