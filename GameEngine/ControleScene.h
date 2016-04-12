#include "Scene.h"

namespace Moo
{
	class ControleScene : public Scene
	{
	public:
		ControleScene();
		~ControleScene();
		bool	run(Moo::Window &window);
		void	clean();
		bool	init(SoundSystem *soundSystem);
	private:
		SoundSystem *soundSystem;
		Moo::Texture *controleText;
		Moo::Sprite *controle;
	};
}