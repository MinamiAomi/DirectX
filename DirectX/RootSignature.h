#pragma once
namespace DirectXHepler {
	using namespace Microsoft::WRL;

	class RootSignatureDesc {
	public:
		enum class DescriptorType {
			CBV = D3D12_ROOT_PARAMETER_TYPE_CBV,
			SRV = D3D12_ROOT_PARAMETER_TYPE_SRV,
			UAV = D3D12_ROOT_PARAMETER_TYPE_UAV
		};

		enum class RangeType {
			SRV = D3D12_DESCRIPTOR_RANGE_TYPE_SRV,
			UAV = D3D12_DESCRIPTOR_RANGE_TYPE_UAV,
			CBV = D3D12_DESCRIPTOR_RANGE_TYPE_CBV,
			Sampler = D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER
		};

		enum class AddressMode {
			Wrap = D3D12_TEXTURE_ADDRESS_MODE_WRAP,
			Mirror = D3D12_TEXTURE_ADDRESS_MODE_MIRROR,
			Clamp = D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
			Border = D3D12_TEXTURE_ADDRESS_MODE_BORDER,
			MirrorOnce = D3D12_TEXTURE_ADDRESS_MODE_MIRROR_ONCE
		};

		operator const D3D12_ROOT_SIGNATURE_DESC& ();

		void AddDescriptorTable();
		void AddDescriptor(DescriptorType descType, uint32_t shaderRegister, uint32_t registerSpace = 0);
		void AddDescriptorRange(
			RangeType rangeType,
			uint32_t numDescriptors,
			uint32_t baseShaderRegister,
			uint32_t registerSpace = 0,
			uint32_t offset = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND);
		void AddStaticSampler(
			uint32_t shaderRegister,
			uint32_t ragisterSpace = 0,
			D3D12_FILTER filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR,
			AddressMode addressU = AddressMode::Wrap,
			AddressMode addressV = AddressMode::Wrap,
			AddressMode addressW = AddressMode::Wrap);
		void AddFlags(D3D12_ROOT_SIGNATURE_FLAGS flags);
		void Clear();

	private:
		std::vector<std::vector<D3D12_DESCRIPTOR_RANGE>> ranges_;
		std::vector<D3D12_ROOT_PARAMETER> rootParameters_;
		std::vector<D3D12_STATIC_SAMPLER_DESC> staticSamplerDescs_;
		D3D12_ROOT_SIGNATURE_FLAGS flags_ = D3D12_ROOT_SIGNATURE_FLAG_NONE;
		D3D12_ROOT_SIGNATURE_DESC desc_{};

		friend class RootSignature;
	};

	class RootSignature {
	public:
		operator ID3D12RootSignature* () const { return rootSignature_.Get(); }

		bool Initalize(ID3D12Device* device, const D3D12_ROOT_SIGNATURE_DESC& desc);

		bool IsEnabled() const { return rootSignature_; }
		ID3D12RootSignature* Get() const { return rootSignature_.Get(); }
		ComPtr<ID3D12RootSignature> GetComPtr() const { return rootSignature_; }
		ID3D12RootSignature* const* GetAddressOf() const { return rootSignature_.GetAddressOf(); } 

		void SetName(const std::wstring& name);

	private:
		ComPtr<ID3D12RootSignature> rootSignature_;
	};

}
