#include "ship.hpp"
#include <stdexcept>

Ship::Ship(size_t length, Ship::Orientation orientation)
    : orientation_(orientation) {
    segments_.resize(length, SegmentState::INTACT);
}

Ship::~Ship() = default;

const std::vector<SegmentState>& Ship::get_segments() const {
    return segments_;
}

void Ship::set_state(size_t index) {
    if (index >= segments_.size()) {
        throw std::out_of_range("Invalid segment index for setting state.");
    }
    if (segments_[index] == SegmentState::INTACT) {
        segments_[index] = SegmentState::DAMAGED;
    } else if (segments_[index] == SegmentState::DAMAGED) {
        segments_[index] = SegmentState::DESTROYED;
    }
}

const SegmentState& Ship::get_segment(size_t index) const {
    if (index >= segments_.size()) {
        throw std::out_of_range("Invalid segment index for getting state.");
    }
    return segments_[index];
}

Ship::Orientation Ship::get_orientation() const {
    return orientation_;
}

size_t Ship::size() const {
    return segments_.size();
}
