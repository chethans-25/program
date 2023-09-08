module hello;
reg [10:0]i;
initial
begin
i = 10'h1z;
$display("Hello worldd");
$display("i=%b",^i);
end
endmodule