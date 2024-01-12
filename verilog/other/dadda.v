
module dadda_multiplier (
  input wire clk,
  input wire [11:0] a,
  input wire [11:0] b,
  output reg [23:0] result
);

reg [11:0] pp[4:0][2:0];

always @(posedge clk) begin
  // Generate partial products
  for (int i = 0; i < 5; i = i + 1) begin
    for (int j = 0; j < 3; j = j + 1) begin
      pp[i][j] = a[i] & b[j];
    end
  end

  // Generate sum and propagate signals
  reg [5:0] g[4:0][2:0];
  reg [5:0] p[4:0][2:0];
  for (int i = 0; i < 5; i = i + 1) begin
    for (int j = 0; j < 3; j = j + 1) begin
      g[i][j] = pp[i][j];
      p[i][j] = pp[i][j];
    end
  end

  // Generate group signals
  reg [5:0] group[4:0];
  for (int i = 0; i < 5; i = i + 1) begin
    group[i] = g[i][0] | (p[i][0] & g[i][1]) | (p[i][0] & p[i][1] & g[i][2]);
  end

  // Generate sum and propagate signals for the second level
  reg [11:0] sum[4:0];
  reg [11:0] propagate[4:0];
  for (int i = 0; i < 5; i = i + 1) begin
    sum[i] = pp[i][2] ^ g[i][2];
    propagate[i] = pp[i][2] & g[i][2];
  end

  // Generate carry signals for the third level
  reg [23:0] carry[4:0];
  carry[0] = group[0];
  for (int i = 1; i < 5; i = i + 1) begin
    carry[i] = group[i] | (propagate[i-1] & carry[i-1]);
  end

  // Generate final result
  result <= {sum[4], sum[3], sum[2], sum[1], sum[0], carry[4]};
end

endmodule
