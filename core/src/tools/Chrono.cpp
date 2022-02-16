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
    t += ImGui::GetIO().DeltaTime;
    static float history = 10.0f;
    static bool isShaded = false;
    static bool isAutoFit = true;
    static bool isRealTime = true;
    static double drag_tag = 0;
    static int numOfGraph = 1;

    ImGui::Begin("PlotLineTest");

    auto frameHeight = ImGui::GetWindowHeight() - 80;
    ImGui::BeginChild("DND_LEFT", ImVec2(100, frameHeight));
    if (ImGui::Button("Reset Data")) {
        for (auto &it: _values) {
            it.second.Plt = -1;
        }
    }
    for (auto &it: _values) {
        if (it.second.Plt > -1)
            continue;
        // ImPlot::ItemIcon(color);
        // ImGui::SameLine();
        ImGui::Selectable(it.second._name.c_str(), false, 0, ImVec2(100, 0));
        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
            ImGui::SetDragDropPayload("MY_DND", &it.first, sizeof(uint64));
            // ImPlot::ItemIcon(dnd[k].Color);
            ImGui::SameLine();
            ImGui::TextUnformatted(it.second._name.c_str());
            ImGui::EndDragDropSource();
        }
    }
    ImGui::EndChild();
    if (ImGui::BeginDragDropTarget()) {
        if (const ImGuiPayload *payload =
                ImGui::AcceptDragDropPayload("MY_DND")) {
            const uint64 it = *(const uint64 *)payload->Data;
            _values.find(it)->second.Plt = -1;
        }
        ImGui::EndDragDropTarget();
    }

    ImGui::SameLine();
    ImGui::BeginGroup();

    ImGui::SliderFloat("History", &history, 1, 30, "%.1f s");
    ImGui::SameLine();
    ImGui::Checkbox("Shaded", &isShaded);
    ImGui::SameLine();
    ImGui::Checkbox("AutoFit", &isAutoFit);
    ImGui::SameLine();
    ImGui::Checkbox("RealTime", &isRealTime);
    if (numOfGraph < 4) {
        ImGui::SameLine();
        if (ImGui::Button("+"))
            numOfGraph += 1;
    }
    if (numOfGraph > 1) {
        ImGui::SameLine();
        if (ImGui::Button("-")) {
            for (auto &it: _values) {
                if (it.second.Plt == numOfGraph - 1)
                    it.second.Plt = -1;
            }
            numOfGraph -= 1;
        }
    }

    for (int index = 0; index < numOfGraph; index++) {
        if (ImPlot::BeginPlot(("##plotTest" + std::to_string(index)).c_str(),
                ImVec2(-1, frameHeight / numOfGraph))) {
            ImPlot::SetupAxes("", "Time [ms]", ImPlotAxisFlags_None,
                isAutoFit ? ImPlotAxisFlags_AutoFit : ImPlotAxisFlags_None);
            ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 50);
            ImPlot::SetNextFillStyle(IMPLOT_AUTO_COL, 0.5f);
            // ImPlot::DragLineY(
            //     0, &drag_tag, ImVec4(1, 1, 0, 1), 1,
            //     ImPlotDragToolFlags_NoFit);
            // ImPlot::TagY(
            //     drag_tag, ImVec4(1, 1, 0, 1),
            //     std::to_string(drag_tag).c_str());

            for (auto &it: _values) {
                if (it.second.Plt == index) {
                    // ImPlot::TagY(it.second._maxValue, ImVec4(1, 0, 0, 1));
                    // ImPlot::TagY(it.second._minValue, ImVec4(0, 1, 0, 1));
                    if (isRealTime)
                        ImPlot::SetupAxisLimits(
                            ImAxis_X1, t - history, t, ImGuiCond_Always);
                    if (it.second.isPlot == true) {
                        ImPlot::PlotScatter(it.second._name.c_str(),
                            &it.second.Data[0].x, &it.second.Data[0].y,
                            it.second.Data.size(), it.second.Offset,
                            2 * sizeof(float));
                    } else if (isShaded) {
                        ImPlot::PlotShaded(it.second._name.c_str(),
                            &it.second.Data[0].x, &it.second.Data[0].y,
                            it.second.Data.size(), 0, it.second.Offset,
                            2 * sizeof(float));
                    } else {
                        ImPlot::PlotLine(it.second._name.c_str(),
                            &it.second.Data[0].x, &it.second.Data[0].y,
                            it.second.Data.size(), it.second.Offset,
                            2 * sizeof(float));
                    }
                    if (ImPlot::BeginDragDropSourceItem(
                            it.second._name.c_str())) {
                        ImGui::SetDragDropPayload(
                            "MY_DND", &it.first, sizeof(uint64));
                        // ImPlot::ItemIcon(dnd[k].Color);
                        ImGui::SameLine();
                        ImGui::TextUnformatted(it.second._name.c_str());
                        ImPlot::EndDragDropSource();
                    }
                }
            }
            if (ImPlot::BeginDragDropTargetPlot()) {
                if (const ImGuiPayload *payload =
                        ImGui::AcceptDragDropPayload("MY_DND")) {
                    const uint64 it = *(const uint64 *)payload->Data;
                    _values.find(it)->second.Plt = index;
                }
                ImPlot::EndDragDropTarget();
            }
            if (ImPlot::BeginDragDropTargetLegend()) {
                if (const ImGuiPayload *payload =
                        ImGui::AcceptDragDropPayload("MY_DND")) {
                    const uint64 it = *(const uint64 *)payload->Data;
                    _values.find(it)->second.Plt = index;
                }
                ImPlot::EndDragDropTarget();
            }
            ImPlot::EndPlot();
        }
    }
    ImGui::EndGroup();

    ImGui::End();
}

void Chrono::start()
{
    _starts.push_back(std::chrono::high_resolution_clock::now());
}

void Chrono::event(std::string name)
{
    auto list = GetValuesList(name);
    list->isPlot = true;
    if (list->Data.size() > 0 && t - list->Data.back().x < 0.5) {
        list->Data.back().y += 1;
    } else
        list->AddPoint(t, 1);
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
    list->AddPoint(t, int_s.count());
}
} // namespace tools