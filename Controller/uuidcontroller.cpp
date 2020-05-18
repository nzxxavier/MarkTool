#include "uuidcontroller.h"

UUIDController::UUIDController()
{

}

QString UUIDController::getUUID()
{
    return QUuid::createUuid().toString();
}
