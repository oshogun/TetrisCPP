template <typename Asset, typename Identifier>
void AssetHolder<Asset,Identifier>::loadAssetFromFile(Identifier id, const std::string & filename)
{
	std::unique_ptr<Asset> asset(new Asset());
	if (!asset->loadFromFile(filename))
		throw std::runtime_error("AssetHolder::loadAssetFromFile() - failed to load file " + filename);
	insertAsset(id, std::move(asset));
}

template <typename Asset, typename Identifier>
template <typename Parameter>
void AssetHolder<Asset,Identifier>::loadAssetFromFile(Identifier id, const std::string & filename, const Parameter& secondParam)
{
    std::unique_ptr<Asset> asset(new Asset());
    if (!asset->loadFromFile(filename, secondParam))
        throw std::runtime_error("AssetHolder::load - Failed to load " + filename);

    insertAsset(id, std::move(asset));
}

template <typename Asset, typename Identifier>
Asset & AssetHolder<Asset, Identifier>::getAssetById(Identifier id)
{
    auto found = assetMap.find(id);
    assert(found != assetMap.end());

    return *found->second;
}

template <typename Asset, typename Identifier>
const Asset & AssetHolder<Asset, Identifier>::getAssetById(Identifier id) const
{
    auto found = assetMap.find(id);
    assert(found != assetMap.end());

    return *found->second;
}

template <typename Asset, typename Identifier>
void AssetHolder<Asset, Identifier>::insertAsset(Identifier id, std::unique_ptr<Asset> asset)
{
    auto inserted = assetMap.insert(std::make_pair(id, std::move(asset)));
    assert(inserted.second);
}