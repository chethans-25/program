
//self checking test bench for 8*8 dadda
module dadda_8TB();


parameter M=8,N=8;

reg [N-1:0]A;
reg [M-1:0]B;
wire [N+M-1:0]Y;



//---- Instantiation of main test module----
//Array_MUL_USign #(64,64) UUT(A,B,Y); //M=4,N=6
 dadda_8 UUT(.A(A),.B(B),.y(Y));


// initializing the inputs to the test module
// initial block executes only once
initial
repeat(1)
begin
	// #10 A = $random; B = $random;
	#10 A = 250; B = 250;
	#100//give required simulation time to complete the operation one by one.
	#100
	#10
	//-----VERIFICATION OF THE OBTAINED RESULT WITH EXISTING RESULT------
	$display(" A=%d,B=%d,AxB=%d",(A),(B),(Y));

	if( (A)*(B) != (Y)) 
		$display(" *ERROR* ");

end

endmodule


