#ifndef CELL_H
#define CELL_H
#include <string>

using std::string;

class Cell
{
    public:
        Cell(int x, int y, string type, string iconFile);
        virtual ~Cell();
        void run();
        int getX();
        int getY();
        string getIconFile();
    protected:
    private:
        int x, y;
        //wxBitmap* icon;
        string type, iconFile;

        //void setIcon(wxBitmap icon);
        void setType(string type);
        string getType();
        void setIconFile(string IconFile);

};

#endif // CELL_H
