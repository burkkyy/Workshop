#pragma once

#include <string>
#include <vector>

namespace wv{
class WvPipeline{
    public:
        WvPipeline(const std::string& vert_filepath, const std::string& frag_filepath);

    private:
        static std::vector<char> read_file(const std::string& filepath);

        void create_graphics_pipline(const std::string& vert_filepath, const std::string& frag_filepath);
};
}
