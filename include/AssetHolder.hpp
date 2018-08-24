#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include <stdexcept>
#include <cassert>

/**
 * @brief      Class for the Asset holder
 *
 * @tparam     Asset       the type of asset to be held by the asset map
 * @tparam     Identifier  the key to acess the asset map
 */
template<typename Asset, typename Identifier>
class AssetHolder {	
public:
	/**
	 * @brief      Loads an asset from file.
	 *
	 * @param[in]  id        The identifier
	 * @param[in]  filename  The filename
	 */
	void loadAssetFromFile(Identifier id, const std::string & filename);
	/**
	 * @brief      Loads an asset from file.
	 *
	 * @param[in]  id         The identifier
	 * @param[in]  filename   The filename
	 * @param[in]  param      The parameter
	 *
	 * @tparam     Parameter a second parameter the load from file function may need
	 */
	template <typename Parameter>
	void loadAssetFromFile(Identifier id, const std::string & filename, const Parameter & param);
	/**
	 * @brief      Gets the asset by identifier.
	 *
	 * @param[in]  id    The identifier
	 *
	 * @return     The asset by identifier.
	 */
	Asset & getAssetById(Identifier id);
	
	/**
	 * @brief      Gets the asset by identifier.
	 *
	 * @param[in]  id    The identifier
	 *
	 * @return     The asset by identifier.
	 */
	const Asset & getAssetById(Identifier id) const;

	/**
	 * @brief      Inserts an asset into the asset map
	 *
	 * @param[in]  id     The identifier
	 * @param[in]  asset  The asset
	 */
	void insertAsset(Identifier id, std::unique_ptr<Asset> asset);
private:
	std::unordered_map<Identifier, std::unique_ptr<Asset>> assetMap;
};

#include "AssetHolder.inl"