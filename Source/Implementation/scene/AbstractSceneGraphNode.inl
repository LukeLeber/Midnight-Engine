namespace midnight
{
    const std::vector<std::shared_ptr<SceneGraphNode>>& AbstractSceneGraphNode::getChildren() const
    {
        return this->children;
    }

    void AbstractSceneGraphNode::add(std::shared_ptr<SceneGraphNode> child)
    {
        this->children.push_back(child);
    }

    void AbstractSceneGraphNode::render(const Camera& camera)
    {
        for(const auto& child : children)
        {
            child->render(camera);
        }
    }
}
