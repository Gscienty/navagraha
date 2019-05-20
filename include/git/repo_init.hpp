#ifndef _NAVAGRAHA_GIT_REPO_INIT_H
#define _NAVAGRAHA_GIT_REPO_INIT_H

#include "extensions/static_constructable.hpp"
#include <git2/repository.h>
#include <string>

namespace navagraha {
namespace git {

class repo_init : extensions::static_constructable<repo_init> {
private:
    git_repository * repo_handler;
    git_remote * template_remote;
    std::string repo_path;
    std::string github_uri;
    std::string template_path;

    void set_template_remote();
    void merge();
    void perform_fastforward(const git_oid * target_oid, bool is_unborn);
public:
    repo_init(std::string repo_path, std::string github_uri, std::string template_path);
    virtual ~repo_init();
    static void static_construct();

    void init();

    void fetch_template();
};

}
}

#endif
