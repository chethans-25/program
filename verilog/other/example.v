module Example;
  reg clk, reset;
  
  always #5 clk = ~clk;
  initial begin
    $monitor("Time: %0t - clk = %b, reset = %b", $time, clk, reset);
    #100 reset = 1;
    #200 reset = 0;
    #300 $finish;
  end
endmodule
