#include "TestApp.h"

int main(int argc, char** argv) {
    auto app = darnel::CreateApplication();
    app->Run();
    delete app;
}
