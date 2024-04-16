#pragma once
#include "wx/wx.h"

class MainWindow;

class DrawingPanel :
    public wxPanel
{
private:
    wxGraphicsContext* pGraphicsContext = nullptr; //a drawing surface
    float& gridSize; //size of the grid
    std::vector<std::vector<bool>>& rGameBoard; //a reference to the game board
public:
    DrawingPanel(MainWindow* window);
    ~DrawingPanel();
};

