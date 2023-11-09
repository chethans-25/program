module test;
logic a,b,c,q;
initial begin
$monitor("[%0t] a=%0b b=%0b c=%0b q=%0b", $time,a,b,c,q );
a <= 0;
b<= 0;
c<= 0;
q<=0;
#5 a <= 1;
C<= 1;
q<= #5a&b/c
#20;
end
endmodule