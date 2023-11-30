#ifndef NPC_H
#define NPC_H

class NPC
{
    private:
        double x,y,r;
    public:
        NPC();
        double returnX();
        double returnY();
        void movement();
};

NPC::NPC()
{
    x = 0;
    y = 0;
    r = 0;
}


#endif 