#pragma once

namespace nano {
	namespace asset {
		class Asset;
} }

namespace nano { namespace ecs { 

	class Entity;

	class Component {
	protected:
		Entity* m_owner;

	public:
		virtual ~Component() { }

		//////////
		// \brief Init called after the component has been added to entity
		//
		virtual void Init() { }

		//////////
		// \brief Start called by entity owner
		//
		virtual void Start() { }

		//////////
		// \brief Update called by entity owner
		//
		virtual void Update() { }

		/////////
		// \brief FixedUpdate called by entity owner
		virtual void FixedUpdate() { }

		//////////
		// \brief Called on new asset load on component
		//
		virtual bool LoadAsset(asset::Asset* a_assetPtr) { return false; }

		//////////
		// \brief Returns this components owner
		//
		Entity& GetEntityOwner();
		//////////
		// \brief Sets this components owner
		//
		void SetEntityOwner(const Entity* a_entity);
	};

} } 