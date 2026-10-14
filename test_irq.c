
extern void HandleControllerFrameInterrupt(void);
extern void CheckAndHandleControllerInterrupt(void);
extern void* g_MovieIRQMainHandler;

void SetupControllerIRQHandlers(void) {
    void* volatile* handlers = (void* volatile*)&g_MovieIRQMainHandler;
    handlers[0] = HandleControllerFrameInterrupt;
    handlers[1] = CheckAndHandleControllerInterrupt;
    handlers[-1] = 0;
    handlers[2] = 0;
}
