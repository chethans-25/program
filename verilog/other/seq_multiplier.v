module seq_multiplier(start,word1,word2,clk,rst,product,ready);
input start,clk,rst;
parameter n=4;
input [n-1:0] word1,word2;
input clk,rst;
output [2*n-1:0] product;
output ready;
wire m0,load,add,shift;
control_unit A(start,clk,rst,m0,ready,load,add,shift);
datapath_unit B(add,shift,load,word1,word2,product,m0,clk,rst);
endmodule

module control_unit(start,clk,rst,m0,ready,load,add,shift);
input start,clk,rst,m0;
output reg ready,load,add,shift;
reg [3:0] ps,ns;
parameter [3:0] s_idle=4'h0,s1=4'h1,s2=4'h2,s3=4'h3,s4=4'h4,s5=4'h5,s6=4'h6,s7=4'h7,s8=4'h8;

//next state logic
always@(ps,m0,start)
begin
add=0;shift=0;load=0;ready=0;
case(ps)
  s_idle:if(start) ns=s1;
         else ns=s_idle;
  s1    :if(m0) ns=s2;
         else if(~m0) ns=s3;
  s2    :ns=s3;
  s3    :if(m0) ns=s4;
         else if(~m0) ns=s5;
  s4    :ns=s5;
  s5    :if(m0) ns=s6;
         else if(~m0) ns=s7;
  s6    :ns=s7;
  s7    :ns=s8;
  s8    :if(start) ns=s1;
         else ns=s8;
default: ns=s_idle;
endcase
end

//ff logic
always@(posedge clk)
if(rst) ps<=s_idle;
else ps<=ns;

//output logic
always@(m0,ps,start)
case(ps)
  s_idle:if(start) 
         begin
         load=1;ready=1;
         end
  s1    :if(m0) add=1;
         else shift=1;
  s2    :shift=1;
  s3    :if(m0) add=1;
         else shift=1;
  s4    :shift=1;
  s5    :if(m0) add=1;
         else if(~m0) shift=1;
  s6    :shift=1;
  s7    :if(m0) add=1;
  s8    :if(start)
         begin 
         ready=1;load=1;
         end
default:begin add=0;shift=0;load=0;ready=0; end
endcase
endmodule


module datapath_unit(add,shift,load,word1,word2,product,m0,clk,rst);
input add,shift,load,clk,rst;
parameter n=4;
input [n-1:0] word1,word2;
input clk,rst;
output reg [2*n-1:0] product;
output m0;
assign m0=pro[0];
reg [n-1:0] mult;
reg [n-1:0] mulp;
reg [2*n-1:0] pro;
always@(posedge clk)
if(rst) 
begin 
mult<=0;pro<=0;mulp<=0;
end
else if(load) 
begin
mult<=word1;pro<=0;mulp<=word2;
end
else if(add) pro<=pro+mult;
else if(shift)
begin 
pro<={pro[n-2:0],1'b0};
mulp<={1'b0,mulp[n-1:1]};
end

assign proudct=pro;
endmodule