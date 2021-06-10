export module DirectX11;
import RendererAPI;

export namespace Florencia {

	class DirectX11 : public RendererAPI {
	public:
		DirectX11();

		void Init() override;

		void Clear() override;
		void SetClearColor(const FloMath::Vec4<float>& color) override;
	private:

	};

}