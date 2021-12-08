#ifndef D2SMODES_H_
#define D2SMODES_H_

/**
 * Enum FrameworkUserMode
 * EngineeringMode: all labels executed dynamically
 * LearningMode: labels will be saved to disk and burstLabels get generated
 * ProductionMode: framework will use pre-defined labels
 * DefaultMode: outside of d2s_BEGIN/END-block
 */

enum d2sWorkModeType {
    LearningMode = 0,
    ProductionMode = 1
};

namespace d2sFrameWorkModeType {

    enum Enum {
        LearningMode = 1, ProductionMode = 2, DefaultMode = 3, EngineeringMode = 0
    };
}

namespace d2sExecutionModeType {

    enum Enum {
        NONE = 0, FUNCTIONAL_TST = 1, EXECUTE_TST = 2, DIGITAL_CAPTURE_TST = 3, SMC_FUNCTIONAL_TST = 4, SMC_EXECUTE_TST = 5, SMC_DIGITAL_CAPTURE_TST = 6,
    }; //,
}
#endif
