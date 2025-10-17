#ifndef PREY_H
#define PREY_H
#include "colony.h"

class Fox;
class Owl;
class Wolf;


class Prey : public Colony {
    public:
        Prey(){}
        Prey(const std::string &n, const char &s, const int a) : Colony(n, s, a) {};
        virtual Prey* attack(Fox *p) = 0;
        virtual Prey* attack(Wolf *p) = 0;
        virtual Prey* attack(Owl *p) = 0;
        virtual ~Prey(){}
};

class Lemming : public Prey {
    public:
        Lemming(const std::string &n, const char &s, const int a) : Prey(n, s, a) {}
        static Lemming* instance();
        Prey* attack(Fox  *p) override;
        Prey* attack(Wolf *p) override;
        Prey* attack(Owl  *p) override;
        static void destroy();
    private:
        static Lemming* _instance;
    protected:
        Lemming(){}
};
class Hare : public Prey {
    public:
        Hare(const std::string &n, const char &s, const int a) : Prey(n, s, a) {}
        static Hare* instance();
        Prey* attack(Fox  *p) override;
        Prey* attack(Wolf *p) override;
        Prey* attack(Owl  *p) override;
        static void destroy();
    private:
        static Hare* _instance;
    protected:
        Hare(){}
};
class Gopher : public Prey {
    public:
        Gopher(const std::string &n, const char &s, const int a) : Prey(n, s, a) {}
        static Gopher* instance();
        Prey* attack(Fox  *p) override;
        Prey* attack(Wolf *p) override;
        Prey* attack(Owl  *p) override;
        static void destroy();
    private:
        static Gopher* _instance;
    protected:
        Gopher(){}
};

#endif // PREY_H
