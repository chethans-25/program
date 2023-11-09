module try;
reg [31:0] random_number;
initial
begin random_number = $random % 100;
$display("Random Number: %d", random_number);
end 
endmodule