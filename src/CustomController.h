#ifndef DSAP_CUSTOM_CONTROLLER_H
#define DSAP_CUSTOM_CONTROLLER_H

#include "ISnakeController.h"
#include "DirectionType.h"

class CustomController : public ISnakeController {
public:
    DirectionType NextDirection(const Game&, size_t) override {
        return DirectionType::kRight;
    }
    
};

#endif // DSAP_CUSTOM_CONTROLLER_H
