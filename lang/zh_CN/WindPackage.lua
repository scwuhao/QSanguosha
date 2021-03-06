-- translation for WindPackage

return {
	["wind"] = "风包", 
	["xiahouyuan"] = "夏侯渊", 
	["caoren"] = "曹仁", 
	["huangzhong"] = "黄忠", 
	["weiyan"] = "魏延", 
	["zhangjiao"] = "张角", 
	["zhoutai"] = "周泰", 
	["jushou"] = "据守", 
	["liegong"] = "烈弓", 
	["kuanggu"] = "狂骨", 
	["guidao"] = "鬼道", 
	["leiji"] = "雷击", 
	["huangtian"] = "黄天", 
	["huangtianv"] = "黄天送牌",
	
	["buqu"] = "不屈", 
	[":buqu"] = "任何时候，当你的体力被扣减到0或更低时，每扣减1点体力：从牌堆亮出一张牌放在你的武将牌上，若该牌的点数与你武将牌上已有的任何一张牌都不同，你可以不死。此牌亮出的时刻为你的濒死状态", 
	["buqu:alive"] = "我还想活",
	["buqu:dead"] = "我不想活了",
	
	["jushou:yes"] = "摸三张牌，若如此做，并将你的武将翻面", 
	["@shensu1"] = "跳过该回合的判定阶段和摸牌阶段, 视为对任意一名角色使用了一张【杀】", 
	["@shensu2"] = "跳过该回合出牌阶段并弃一张装备牌视为对任意一名角色使用了一张【杀】", 
	["$huangtian1"] = "苍天已死，黄天当立", 
	["$huangtian2"] = "岁在甲子，天下大吉", 
	["$jushou1"] = "我先休息一会", 
	["$jushou2"] = "尽管来吧", 
	["$leiji1"] = "以我之真气，合天地之造化", 
	["$leiji2"] = "雷公助我", 
	["$liegong1"] = "百步穿杨", 
	["$liegong2"] = "中！", 
	["$shensu1"] = "吾善于千里袭人", 
	["$shensu2"] = "取汝首级犹如探囊取物", 
	["$buqu1"] = "还不够！", 
	["$buqu2"] = "我绝不会倒下！", 
	["$kuanggu"] = "哈哈",
	["shensu"] = "神速", 
	[":shensu"] = "你可以分别作出下列选择：\
1、跳过该回合的判定阶段和摸牌阶段\
2、跳过该回合出牌阶段并弃一张装备牌\
你每做出上述之一项选择，视为对任意一名角色使用了一张【杀】", 
	[":jushou"] = "回合结束阶段，你可以摸三张牌，若如此做，并将你的武将翻面", 
	[":liegong"] = "出牌阶段，以下两种情况，你可以令你使用的『杀』不可被闪避：1、目标角色的手牌数大于或等于你的体力值。2、目标角色的手牌数小于或等于你的攻击范围\
★攻击范围计算只和武器有关，与+1马-1马无关", 
	[":kuanggu"] = "锁定技，任何时候，你每对与你距离1以内的一名角色造成1点伤害，你回复1点体力", 
	[":guidao"] = "在任意一名角色的判定牌生效前，你可以用自己的一张【黑桃】或【梅花】牌替换之", 
	[":leiji"] = "每当你使用或打出一张【闪】时（在结算前），可令任意一名角色判定，若为【黑桃】，你对该角色造成2点雷电伤害", 
	[":huangtian"] = "主公技，群雄角色可在他们各自的回合里给你一张【闪】或【闪电】", 
	["liegong:yes"] = "此【杀】不可闪避", 
	
	["#KuangguRecover"] = "%from 的锁定技【狂骨】被触发，恢复了 %arg 点体力",
	["@guidao-card"] = "请使用【鬼道】技能来修改 %src 的 %arg 判定",
	
	-- last words
	["~caoren"] = "实在是守不住了……",
	["~xiahouyuan"] = "竟然比我还……快……",
	["~huangzhong"] = "不得不服老了……",
	["~weiyan"] = "谁敢杀我！啊……",
	["~xiaoqiao"] = "公瑾……我先走一步……",
	["~zhoutai"] = "已经尽力了……",
	["~zhangjiao"] = "黄天…也死了……",
}
