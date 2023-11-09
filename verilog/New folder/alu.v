module alu (
    input [31:0]A,B,
    input [2:0]opcode,
    output [31:0]result,
    output ZERO,NEG,OVERFLOW,CARRY
);
    wire [31:0]A_or_B  ; 
    wire [31:0]A_and_B  ;
    wire [31:0]not_B  ;
    wire [31:0]sum ;
    wire [31:0]mux1 ;
    reg [31:0]mux2 ;
    wire cout;

    assign result = mux2;
    assign A_or_B = A|B;
    assign A_and_B  = A&B;
    assign not_B    = ~B;
    assign mux1 = opcode[0]?not_B:B;
    assign {cout,sum} = A + mux1 + opcode[0];
    assign ext = {{31{1'b0}},sum[31]};
    always @(*) begin
        casex(opcode)
        3'b00x:mux2=sum;
        3'b010:mux2=A_and_B;
        3'b011:mux2=A_or_B;
        3'b100:mux2=ext;
        default:mux2=32'd0;
        endcase
    end

    assign ZERO = ~(|result);
    assign NEG = result[31];
    assign CARRY = ~opcode[1]&cout;
    assign OVERFLOW = ~opcode[1]&(A[31]^sum[31])&(~(A[31]^B[31]^opcode[0]));
endmodule