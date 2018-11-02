#!/usr/bin/env python
# -*- coding: utf-8 -*-

from tkinter import *
def drawboard(board,colors,startx=50,starty=50,cellwidth=50):
    width=2*startx+len(board)*cellwidth
    height=2*starty+len(board)*cellwidth
    canvas.config(width=width,height=height)
    for j  in range(len(board)):
        for i in range(len(board)):
 
            index=board[j][i]
            color=colors[6-index]
            cellx=startx+i*50
            celly=starty+j*50
            canvas.create_rectangle(cellx,celly,cellx+cellwidth,celly+cellwidth,
                fill=color,outline="black")
    canvas.update()
root=Tk()
canvas=Canvas(root,bg="white")
canvas.pack()
board=[ [5,1,2,3],
        [2,1,5,6],
        [4,1,1,1],
        [3,6,0,5]]
colors=['teal','lightseagreen','turquoise','paleturquoise','lightcyan','azure','white']
drawboard(board,colors)
root.mainloop()