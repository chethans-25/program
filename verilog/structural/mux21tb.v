`include "mux21.v"
module mux21tb;
reg a,b;
reg sel;

wire y;
mux21 m1 (a,b,sel,y);
initial begin
    $dumpfile("mux21tb.vcd");
    $dumpvars(0,mux21tb);
    a=1'b1;b=1'b0;sel=1'b1;
    #5 sel=1'b0;
    #10 sel =1'b1;
    #5 $finish;
end
endmodule