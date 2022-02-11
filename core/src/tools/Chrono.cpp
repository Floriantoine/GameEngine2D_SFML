#include "tools/Chrono.hpp"

namespace tools {
uint64 Chrono::nameToId(const char *name, size_t length)
{
    uint64 seed;
    return SpookyHash::Hash64(name, length, seed);
}

uint64 Chrono::nameToId(std::string name)
{
    return nameToId(name.c_str(), name.size());
}

bool Chrono::isRegistered(uint64 typeId)
{
    return (_values.find(typeId) != _values.end());
}
std::vector<float> *Chrono::GetValuesList(uint64 id)
{
    if (isRegistered(id) == false) {
        _values[id] = std::vector<float>();
    }
    const auto &it = _values.find(id);
    if (it == _values.end())
        return nullptr;
    return &it->second;
}

Chrono::Chrono(/* args */)
{
    Chrono::_start = std::chrono::high_resolution_clock::now();
}

void Chrono::start()
{
    _start = std::chrono::high_resolution_clock::now();
}
void Chrono::end(std::string name)
{
    auto end = std::chrono::high_resolution_clock::now();
    auto int_s =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - _start);
    uint64 id = nameToId(name);
    auto list = GetValuesList(id);
    list->push_back(int_s.count());
    if (list->size() > 100)
        list->erase(list->begin());
    auto it = std::max_element(list->begin(), list->end());
    ImGui::Begin("PlotLineTest");

    ImGui::PlotHistogram("", &(*list)[0], list->size(), 0, name.c_str(), 0, *it,
        ImVec2(400, 100));
    ImGui::End();
}
} // namespace tools