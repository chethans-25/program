module seq_multiplier_tb()
reg start,clk,rst;
reg [n-1:0] word1,word2;
reg clk,rst;
wire [2*n-1:0] product;
wire ready;
seq_multiplier sm1 (start,word1,word2,clk,rst,product,ready)

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