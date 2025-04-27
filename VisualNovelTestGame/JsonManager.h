#ifndef JSONMANAGER_H
#define JSONMANAGER_H

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class JsonManager {
public:
    // Public fields populated by LoadData()
    std::string line;
    std::string backgroundSprite;
    std::string leftSprite;
    std::string rightSprite;
    std::string audioPath;
    bool        audioLoop{ false };

    JsonManager() = default;
    ~JsonManager() = default;

    /**
     * @brief Load and parse a JSON file containing a top-level "data" array.
     *        Resets iteration state.
     * @param jsonPath Path to the JSON file.
     */
    void LoadJson(const std::string& jsonPath) noexcept;

    /**
     * @brief Advance to the next element in the JSON "data" array.
     *        Populates public fields with values from that element.
     */
    void LoadData() noexcept;

    /** True if LoadData() would fetch another entry */
    [[nodiscard]] bool HasNext() const noexcept { return hasNext_; }

    /** True if a JSON has been successfully loaded (and contains a data array) */
    [[nodiscard]] bool IsLoaded() const noexcept;

    /** Completely reset all state to “empty” */
    void ClearLoads() noexcept;

    /** Clear only the parsed JSON content */
    void ClearAll() noexcept;

private:
    json    jsonCurrent_;
    size_t  currentIndex_{ 0 };
    bool    hasNext_{ false };

    void UpdateHasNext() noexcept;
};

#endif // JSONMANAGER_H