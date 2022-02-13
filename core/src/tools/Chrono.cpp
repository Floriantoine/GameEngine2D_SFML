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
ImplotPerfInf *Chrono::GetValuesList(std::string name)
{
    uint64 id = nameToId(name);

    if (isRegistered(id) == false) {
        _values[id] = ImplotPerfInf(name);
    }
    const auto &it = _values.find(id);
    if (it == _values.end())
        return nullptr;
    return &it->second;
}

Chrono::Chrono(/* args */)
{
}
Chrono::~Chrono(/* args */)
{
    _values.clear();
}

void Chrono::display()
{
    static ImPlotAxisFlags flags = ImPlotAxisFlags_NoTickLabels;
    t += ImGui::GetIO().DeltaTime;
    static float history = 10.0f;

    ImGui::Begin("PlotLineTest");

    ImGui::SliderFloat("History", &history, 1, 30, "%.1f s");
    ImPlot::BeginPlot("plotTest");
    ImPlot::SetupAxes("", "Time [ms]");
    ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 50);
    ImPlot::SetNextFillStyle(IMPLOT_AUTO_COL, 0.5f);

    for (auto &it: _values) {
        ImPlot::SetupAxisLimits(ImAxis_X1, t - history, t, ImGuiCond_Always);
        ImPlot::PlotShaded(it.second._name.c_str(), &it.second.Data[0].x,
            &it.second.Data[0].y, it.second.Data.size(), 0, it.second.Offset,
            2 * sizeof(float));
        // ImPlot::PlotLine(it.second._name.c_str(), &it.second.Data[0].x,
        //     &it.second.Data[0].y, it.second.Data.size(), it.second.Offset,
        //     2 * sizeof(float));
    }
    ImPlot::EndPlot();
    ImGui::End();
}

void Chrono::start()
{
    _starts.push_back(std::chrono::high_resolution_clock::now());
}
void Chrono::end(std::string name)
{
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::_V2::system_clock::time_point start =
        _starts[_starts.size() - 1];
    _starts.pop_back();

    auto int_s =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    auto list = GetValuesList(name);
    std::cout << "point: " << list->Data.size() + list->Offset << std::endl;
    list->AddPoint(t, int_s.count());
}
} // namespace tools