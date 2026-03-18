//#pragma once
//#include <unordered_map>
//#include <string>
//
//struct AnimState
//{
//    int attachIndex = -1;
//    float totalTime = 0.0f;
//    float nowTime = 0.0f;
//    bool isLoop = false;
//    std::string nowAnim;
//};
//
//class AnimationManager
//{
//public:
//    // Meyers シングルトン（スレッド安全）
//    static AnimationManager* GetInstance();
//
//    void Load();
//    void Fin();
//
//    void RegisterAnimations(int handle, const std::unordered_map<std::string, int>& animMap);
//    void PlayAnimation(int handle, const std::string& animName, bool isLoop);
//    void UpdateAnimation(int handle);
//    float GetCurrentFrame(int handle);
//    bool CheckAnimationFinish(int handle);
//    bool IsPlaying(int handle, const std::string& animName);
//    bool IsFinished(int handle, const std::string& animName);
//
//private:
//    AnimationManager();
//    ~AnimationManager();
//
//    // コピー禁止
//    AnimationManager(const AnimationManager&) = delete;
//    AnimationManager& operator=(const AnimationManager&) = delete;
//
//    // キー: モデルハンドル -> (アニメ名 -> アニメインデックス)
//    std::unordered_map<int, std::unordered_map<std::string, int>> m_AnimNameToIndex;
//    std::unordered_map<int, AnimState> m_AnimStates;
//    bool m_IsAnimationFinished = false;
//};