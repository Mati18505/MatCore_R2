#pragma once

class GPUResource
{
public:
	GPUResource() = default;
	virtual ~GPUResource() = default;
	GPUResource(const GPUResource& other) = delete;
	GPUResource(GPUResource&& other) noexcept = delete;
	GPUResource& operator=(const GPUResource& other) = delete;
	GPUResource& operator=(GPUResource&& other) noexcept = delete;
};