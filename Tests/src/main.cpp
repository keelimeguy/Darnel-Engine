#include "TestApp.h"

int main(int argc, char** argv) {
    auto app = std::unique_ptr<darnel::Application>(darnel::CreateApplication());
    app->Run();
}
