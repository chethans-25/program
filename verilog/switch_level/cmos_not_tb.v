// `include "cmos_not.v"

module cmos_not_tb();
reg in;
wire out;
cmos_not not1(out,in);
initial
begin
    $dumpfile("cmos_not_tb.vcd");
    $dumpvars(0,cmos_not_tb);
    in=0;
    #1 in=1;
    #1 in=0;
    #1 in=1;
    #1 in=0;
    #1 in=1;
    #1 in=0;
    #1 $finish;
end

endmodule