// #pragma once
#ifndef HANDLER_H
#define HANDLER_H

#include "wintoastlib.h"
using namespace WinToastLib;

class WinToastHandlerExample : public IWinToastHandler {
    public:
        void toastActivated() const {
            std::cout << "The user clicked in this toast" << std::endl;
            // exit(0);
        }
    
        void toastActivated(int actionIndex) const {
            std::cout << "The user clicked on action #" << actionIndex << std::endl;
            // exit(16 + actionIndex);
        }
    
        void toastActivated(const char* response) const {
            std::cout << "The user clicked on action #" << response << std::endl;
        }
    
        void toastDismissed(WinToastDismissalReason state) const {
            switch (state) {
                case UserCanceled:
                    std::cout << "The user dismissed this toast" << std::endl;
                    // exit(1);
                    break;
                case TimedOut:
                    std::cout << "The toast has timed out" << std::endl;
                    // exit(2);
                    break;
                case ApplicationHidden:
                    std::cout << "The application hid the toast using ToastNotifier.hide()" << std::endl;
                    // exit(3);
                    break;
                default:
                    std::cout << "Toast not activated" << std::endl;
                    // exit(4);
                    break;
            }
        }
    
        void toastFailed() const {
            std::wcout << L"Error showing current toast" << std::endl;
            exit(5);
        }
    };

extern WinToastHandlerExample* handler;

#endif // HANDLER_H