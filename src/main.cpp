#include <Geode/Geode.hpp>

#include <Geode/modify/RateStarsLayer.hpp>
#include <Geode/modify/ProfilePage.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/SupportLayer.hpp>
#include <Geode/modify/GameManager.hpp>

using namespace geode::prelude;

class $modify(LevelInfoLayer) {

	bool init(GJGameLevel * p0, bool p1) {

		GameManager* manager = GameManager::sharedState();

		manager->m_hasRP = Mod::get()->getSettingValue<int64_t>("mod-type");

		bool result = LevelInfoLayer::init(p0,p1);

		return result;

	}
};


class $modify(RateStarsLayer) {

	void onRate(CCObject * sender) {

		CCLayer* layer = static_cast<CCLayer*>(getChildren()->objectAtIndex(0));

		if (layer->getChildrenCount() == 3) { // prevents it from being shown to the normal star rate
			UploadActionPopup* popup = UploadActionPopup::create(nullptr, "");
			popup->show();
			popup->showSuccessMessage("Rating submitted!");
		}
		else {
			RateStarsLayer::onRate(sender);
		}
	}
};


class $modify(SupportLayer) {

	void onRequestAccess(CCObject * sender) {

		UploadActionPopup* popup = UploadActionPopup::create(nullptr, "");
		popup->show();
		popup->showSuccessMessage("Success! Moderator access granted.");
	}
};


class $modify(ProfilePage) {

CCSprite* icon;

	void setupPageInfo(gd::string name, char const* c) {

		ProfilePage::setupPageInfo(name, c);

		if (m_ownProfile) {

			// Thanks for this code Xanii | you're welcome

			int mod_type = Mod::get()->getSettingValue<int64_t>("mod-type");

			switch(mod_type) {
				case 1: m_fields->icon = CCSprite::createWithSpriteFrameName("modBadge_01_001.png"); break;
				case 2: m_fields->icon = CCSprite::createWithSpriteFrameName("modBadge_02_001.png"); break;
			}
			
			if (mod_type > 0) {
				CCNode* first_letter = reinterpret_cast<CCNode*>(m_usernameLabel->getChildren()->objectAtIndex(0));

				m_fields->icon->setScale(m_usernameLabel->getScale() + 0.2);
				m_fields->icon->setPosition(first_letter->convertToWorldSpace(getPosition()));
				m_fields->icon->setPosition({ m_fields->icon->getPositionX() - 15.f, m_fields->icon->getPositionY() + 10.f });

				static_cast<CCLayer*>(this->getChildren()->objectAtIndex(0))->addChild(m_fields->icon);
			}
		}
	}
};
