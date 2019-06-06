#include "extensions/tar.hpp"
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <fstream>

namespace navagraha {
namespace extensions {


tar::tar(std::string tar_name, std::string dir)
    : tar_name(tar_name)
    , dir(dir)
{
    if (access(tar_name.c_str(), F_OK) == 0) {
        remove(tar_name.c_str());
    }
    tar_open(&this->tar_handler, const_cast<char *>(tar_name.c_str()), NULL, O_WRONLY | O_CREAT, 0644, TAR_GNU);

    if (*this->dir.rbegin() != '/') {
        this->dir += '/';
    }

    this->fill_ignored();
}

tar::~tar()
{
    tar_close(this->tar_handler);
}

void tar::fill_ignored()
{
    std::string navaignore = this->dir + ".navaignore";
    if (access(navaignore.c_str(), F_OK) != 0) {
        return;
    }

    this->ignored.push_back(extensions::file_wildcards(".navaignore"));
    std::fstream f(navaignore);
    std::filebuf fb;
    fb.open(navaignore.c_str(), std::ios::in);
    std::istream is(&fb);
    std::string line;
    while (std::getline(is, line)) {
        this->ignored.push_back(extensions::file_wildcards(line));
    }
    fb.close();
}

bool tar::ignore(const std::string & filename, bool is_file)
{
    bool ret = false;
    std::string ignore_check_name(filename.begin() + 1, filename.end());
    for (std::list<extensions::file_wildcards>::const_iterator iter = std::begin(this->ignored);
         iter != std::end(this->ignored);
         iter++) {
        if (iter->match(ignore_check_name, is_file)) {
            if (iter->exclude()) {
                return false;
            }
            ret = true;
        }
    }

    return ret;
}

void tar::direct_each(std::string real_direct_name, std::string logic_direct_name)
{
    int ret;
    DIR * dir = opendir(real_direct_name.c_str());
    if (dir == NULL) {
        return;
    }
    for (dirent * node = readdir(dir); node; node = readdir(dir)) {
        std::string log_path = logic_direct_name + std::string(node->d_name);
        std::string real_path = real_direct_name + std::string(node->d_name); 
        if (node->d_type == DT_DIR && strcmp(node->d_name, ".") != 0 && strcmp(node->d_name, "..") != 0) {
            if (this->ignore(log_path, false) == false) {
                this->direct_each(real_path + '/', log_path + '/');
            }
        }
        else if (node->d_type != DT_DIR) {
            if (this->ignore(log_path, true) == false) {
                ret = tar_append_file(this->tar_handler, const_cast<char *>(real_path.c_str()), const_cast<char *>(log_path.c_str()));
            }
        }
    }
    closedir(dir);
}

void tar::operator() ()
{
    this->direct_each(this->dir, "./");
    tar_append_eof(this->tar_handler);
}

size_t tar::size() const
{
    int fd = open(this->tar_name.c_str(), O_RDONLY);
    lseek(fd, 0, SEEK_END);
    size_t ret = lseek(fd, 0, SEEK_CUR);
    close(fd);
    return ret;
}

void tar::extract(std::string & str)
{
    size_t tar_size = this->size();
    str.resize(tar_size);
    int fd = open(this->tar_name.c_str(), O_RDONLY);
    read(fd, const_cast<char *>(str.data()), tar_size);
    close(fd);
}

}
}
