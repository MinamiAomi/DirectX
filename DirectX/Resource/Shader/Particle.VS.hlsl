#include "Particle.hlsli"

struct VertexShaderInput {
	float32_t4 position : POSITION0;
};

struct VertexShaderOutput {
	float32_t4 position : POSITION0;
};

VertexShaderOutput main(VertexShaderInput input) {
	VertexShaderOutput output;
	output.position = mul(input.position, g_transformCB.viewMatrix);
	return output;
}