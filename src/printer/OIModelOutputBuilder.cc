#include "OIModelOutputBuilder.h"

namespace s2j {
namespace printer {

OIModelOutputBuilder::OIModelOutputBuilder()
    : milliSecondsElapsed_(0), memoryPeakKb_(0), syscallsCounter_(0), exitStatus_(0), killSignal_(0) {}

OutputBuilder& OIModelOutputBuilder::setCyclesUsed(uint64_t cyclesUsed) {
    milliSecondsElapsed_ = cyclesUsed * 1'000 / CYCLES_PER_SECOND;
    return *this;
}

OutputBuilder& OIModelOutputBuilder::setMemoryPeak(uint64_t memoryPeakKb) {
    memoryPeakKb_ = memoryPeakKb;
    return *this;
}

OutputBuilder& OIModelOutputBuilder::setExitStatus(uint32_t exitStatus) {
    if (exitStatus_ == 0) {
        exitStatus_ = exitStatus;
    }
    return *this;
}

OutputBuilder& OIModelOutputBuilder::setKillSignal(uint32_t killSignal) {
    if (killSignal_ == 0) {
        killSignal_ = killSignal;
        setExitStatus(128 + killSignal_);
    }
    return *this;
}

OutputBuilder& OIModelOutputBuilder::setKillReason(KillReason reason, const std::string& comment) {
    // Remember only first kill reason
    if (killReason_ == OK) {
        killReason_ = reason;
        killReasonComment_ = comment;
    }

    return *this;
}

}
}
