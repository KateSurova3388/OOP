#ifndef SHIP_HPP
#define SHIP_HPP

#include <vector>
#include <stdexcept>

enum class SegmentState { INTACT, DAMAGED, DESTROYED };

class Ship {
public:
    enum class Orientation { Horizontal, Vertical };

    Ship(size_t length, Orientation orientation);
    ~Ship();

    const std::vector<SegmentState>& get_segments() const;
    void set_state(size_t index);
    const SegmentState& get_segment(size_t index) const;
    Orientation get_orientation() const;
    size_t size() const;

private:
    Orientation orientation_;
    std::vector<SegmentState> segments_;
};

#endif
