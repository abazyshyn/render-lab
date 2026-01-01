#include "singleton.hpp"
#include "scenes/scene.hpp"

namespace Lab
{

    class CSceneHierarchyPanel : public Utils::CSingleton<CSceneHierarchyPanel>
    {
    public:
        friend Utils::CSingleton<CSceneHierarchyPanel>;

        void SetSceneContext(const std::shared_ptr<CScene> &context) { m_Context = context; };

        void OnImGuiRender();

    private:
        std::shared_ptr<CScene> m_Context;
    };

} // namespace Lab
