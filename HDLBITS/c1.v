module top_module(
    input clk,
    input areset,    // Asynchronous reset to state B
    input in,
    output out);//  

    parameter A=0, B=1; 
    reg state, next_state;
	reg out1;
    assign out=out1;
    always @(state,in) begin    // This is a combinational always block
        // State transition logic
        case(state)
            B:begin
                out1 = 1'b1;
                next_state = in?B:A;end
            A:begin
                out1 = 1'b0;
                next_state = in?A:B;end
        endcase
        
    end

    always @(posedge clk, posedge areset) begin    // This is a sequential always block
        // State flip-flops with asynchronous reset
        if(areset) state <= B;
        else state <= next_state; 
    end

    // Output logic
    // assign out = (state == ...);

endmodule
