//
// Created by batrider(.death) on 8/22/20.
//
#include <iostream>

class print
{
    public:
    [[maybe_unused]] static void clear_screen()
    {
        escape_sequence_start();
        std::cout << "cls\n";
        escape_sequence_stop();
    }

    [[maybe_unused]] static void move_pixel()
    {
        escape_sequence_start();
        std::cout << "move\n";
        escape_sequence_stop();
    }

    private:
    [[maybe_unused]] static void escape_sequence_start()
    {
        std::cout << "start\n";
    }

    [[maybe_unused]] static void escape_sequence_stop()
    {
        std::cout << "stop\n";
    }
};

class execution_print : public print
{
    public:
    [[maybe_unused]] static void arch_linux()
    {
        print::clear_screen();
        std::cout << "arch\n";
    }
};

int main()
{
    execution_print::arch_linux();
    return 0;
}
