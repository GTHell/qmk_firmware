# The GTHEll keymap for Redox
  
The Redox wiring suppose to mirror each other. I didn't notice that so I didn't mirror the slave side which in return, I need to flipped the right side matrix in the rev1/rev1.h.
 
This also affect how Via show my keymaps. It showed the right side flipped along x-axis because the way I wired it. 

To fix this layout, I need to create a new layout with key matrixes using keyboard-layout-editor. 

You can find the matrix that I redesign in *correct-matrix-layout.json* file. Those matrix will produce a correct layout output in Via.

To fit the Redox design, I create modify the original layout of Redox's keyboard-layout-editor file and customize it with the correct matrix.

You can fine the layout in gthell.json or go to link below.




http://www.keyboard-layout-editor.com/##@_name=Redox&author=Mattia%20Dal%20Ben&switchMount=cherry&plate:false&pcb:false%3B&@_x:3.5%3B&=0,3&_x:10.5%3B&=5,3%3B&@_y:-0.875&x:2.5%3B&=0,2&_x:1%3B&=0,4&_x:8.5%3B&=5,2&_x:1%3B&=5,4%3B&@_y:-0.875&x:5.5%3B&=0,5&_x:6.5%3B&=5,1%3B&@_y:-0.875&x:0.25&w:1.25%3B&=0,0&=0,1&_x:14.5%3B&=5,5&_w:1.25%3B&=5,6%3B&@_y:-0.625&x:6.5%3B&=0,6&_x:4.5%3B&=5,0%3B&@_y:-0.75&x:3.5%3B&=1,3&_x:10.5%3B&=6,3%3B&@_y:-0.875&x:2.5%3B&=1,2&_x:1%3B&=1,4&_x:8.5%3B&=6,2&_x:1%3B&=6,4%3B&@_y:-0.875&x:5.5%3B&=1,5&_x:6.5%3B&=6,1%3B&@_y:-0.875&x:0.25&w:1.25%3B&=1,0&=1,1&_x:14.5%3B&=6,5&_w:1.25%3B&=6,6%3B&@_y:-0.625&x:6.5&h:1.5%3B&=1,6&_x:4.5&h:1.5%3B&=6,0%3B&@_y:-0.75&x:3.5%3B&=2,3&_x:10.5%3B&=7,3%3B&@_y:-0.875&x:2.5%3B&=2,2&_x:1&n:true%3B&=2,4&_x:8.5&n:true%3B&=7,2&_x:1%3B&=7,4%3B&@_y:-0.875&x:5.5%3B&=2,5&_x:6.5%3B&=7,1%3B&@_y:-0.875&x:0.25&w:1.25%3B&=2,0&=2,1&_x:14.5%3B&=7,5&_w:1.25%3B&=7,6%3B&@_y:-0.375&x:3.5%3B&=3,3&_x:10.5%3B&=8,3%3B&@_y:-0.875&x:2.5%3B&=3,2&_x:1%3B&=3,4&_x:8.5%3B&=8,2&_x:1%3B&=8,4%3B&@_y:-0.875&x:5.5%3B&=3,5&_x:6.5%3B&=8,1%3B&@_y:-0.875&x:0.25&w:1.25%3B&=3,0&=3,1&_x:14.5%3B&=8,5&_w:1.25%3B&=8,6%3B&@_y:-0.375&x:3.5%3B&=4,3&_x:10.5%3B&=9,3%3B&@_y:-0.875&x:2.5%3B&=4,2&_x:12.5%3B&=9,4%3B&@_y:-0.75&x:0.5%3B&=4,0&=4,1&_x:14.5%3B&=9,5&=9,6%3B&@_r:15&y:-2.625&x:5.75&w:1.25%3B&=4,4%3B&@_r:30&rx:6.5&ry:4.25&y:-1%3B&=2,6&=3,6%3B&@_h:1.5%3B&=4,5&_h:1.5%3B&=4,6%3B&@_r:-30&rx:13&y:-1&x:-2%3B&=8,0&=7,0%3B&@_x:-2&h:1.5%3B&=9,0&_h:1.5%3B&=9,1%3B&@_r:-15&rx:0&ry:0&y:7.75&x:11.75&w:1.25%3B&=9,2
