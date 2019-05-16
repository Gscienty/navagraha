#include "extensions/tar.hpp"
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

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
}
tar::~tar()
{
    tar_close(this->tar_handler);
}


void tar::direct_each(std::string direct_name)
{
    std::string real_direct_name = this->dir + direct_name;
    DIR * dir = opendir(real_direct_name.c_str());
    if (dir == NULL) {
        return;
    }
    for (dirent * node = readdir(dir); node; node = readdir(dir)) {
        std::string log_path = direct_name + "/" + std::string(node->d_name);
        std::string real_path = this->dir + direct_name + "/" + std::string(node->d_name);
        if (node->d_type == DT_DIR && strcmp(node->d_name, ".") != 0 && strcmp(node->d_name, "..") != 0) {
            this->direct_each(log_path);
        }
        else if (node->d_type != DT_DIR) {
            tar_append_file(this->tar_handler, const_cast<char *>(real_path.c_str()), const_cast<char *>(("." + log_path).c_str()));
        }
    }
    closedir(dir);
    tar_append_eof(this->tar_handler);
}

void tar::operator() ()
{
    this->direct_each("");
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
