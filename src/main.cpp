#include <Geode/Geode.hpp>

#include <Geode/modify/RateStarsLayer.hpp>
#include <Geode/modify/ProfilePage.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>


using namespace geode::prelude;

class $modify(LevelInfoLayer) {

	bool init(GJGameLevel * p0, bool p1) {

		std::vector<BYTE> bytes = { 0x90, 0x90 };

		WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(base::get() + 0x252890), bytes.data(), bytes.size(), nullptr);
		WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(base::get() + 0x252895), bytes.data(), bytes.size(), nullptr);

		if (!LevelInfoLayer::init(p0, p1))
			return false;

		return true;
	}
};

class $modify(RateStarsLayer) {

	void onRate(CCObject * sender) {

		UploadActionPopup* popup = UploadActionPopup::create(nullptr, "");
		popup->show();
		popup->showSuccessMessage("Rating submitted!");
	}
};

class $modify(ProfilePage) {

	virtual TodoReturn setupPageInfo(gd::string name, char const* c) {


		if (m_ownProfile) {

			// Thanks for this code Xanii
			CCSprite* icon;

			icon = CCSprite::create("modBadge.png"_spr);

			CCNode* first_letter = reinterpret_cast<CCNode*>(m_usernameLabel->getChildren()->objectAtIndex(0));

			icon->setScale(m_usernameLabel->getScale() + 0.2);
			icon->setPosition(first_letter->convertToWorldSpace(getPosition()));
			icon->setPosition({ icon->getPositionX() - 15.f, icon->getPositionY() + 10.f });

			static_cast<CCLayer*>(this->getChildren()->objectAtIndex(0))->addChild(icon);
		}
	}
};