# rAthena 中文版（rAthenaZhCN）

> English / 上游原版说明：[README-upstream.md](README-upstream.md)

本仓库基于 [rAthena](https://github.com/rathena/rathena) 官方源码快照（2026-10-06）整理，保留上游目录结构，只叠加中文数据与少量必要配置，方便持续跟进上游更新。

## 一、当前包含的中文内容

| 内容 | 位置 | 数量 |
| --- | --- | --- |
| 职业/任务 NPC 脚本汉化 | `npc/jobs`、`npc/re/mobs`、`npc/re/jobs/novice/academy.txt` | 140 个文件 |
| 自定义 NPC 脚本 | `npc/自定义脚本`（已在 `npc/scripts_custom.conf` 注册） | 34 个 |
| 怪物名称 | `db/re/mob_db.yml` | 2434 条中文（其余 241 条保留英文） |
| 服务器系统消息 | `conf/msg_conf/map_msg.conf` | 合并 867 条中文，英文兜底 |
| 客户端封包版本 | `src/custom/defines_pre.hpp` | `PACKETVER 20250402` |

## 二、编码约定（重要）

- **会发送给客户端的服务端文本必须使用 GBK / CP936**：NPC 脚本、`db/re/mob_db.yml`、`conf/msg_conf/map_msg.conf`，这样中文客户端才能正确显示；
- 源码、README、配置文件注释使用 UTF-8；
- 修改上述数据文件时请保持 GBK，否则游戏内会乱码；GitHub 网页直接查看这些文件会显示乱码，属于正常现象。

## 三、未包含的内容

- 旧项目的自定义源码功能（自动连招、AFK 挂机、约 80 项 `battle_config`、99Max 兼容等）。这些是功能改动而不是汉化内容，需要时再单独移植；
- 客户端文件和客户端汉化（`iteminfo`、`skillinfo`、`msgstringtable` 等）不在本仓库；
- 物品 / 技能 / 任务数据库名称仍为英文（客户端显示不受影响，如需 `getitemname()` 输出中文再补）；
- `char_msg.conf`、`login_msg.conf` 尚无中文。

## 四、构建（Windows + Visual Studio）

1. 安装 Visual Studio 的「使用 C++ 的桌面开发」工作负载；
2. 双击 `build_x64.bat`（首次会自动 CMake 配置，构建目录 `out/build/x64-Release`，程序输出到根目录）；
3. 也可以只编译单个目标：`build_x64.bat map-server`。

## 五、运行

1. 准备 MySQL / MariaDB，导入 `sql-files/main.sql` 和 `sql-files/logs.sql`；
2. 复制 `conf/import-tmpl` 的模板到 `conf/import`（该目录已被 `.gitignore` 忽略），填写数据库账号和 IP；
   同时把 `db/import-tmpl` 复制到 `db/import`、`conf/msg_conf/import-tmpl` 复制到 `conf/msg_conf/import`；
3. 双击 `runserver.bat` 启动 login / char / map / web 四个服务。

## 六、与上游同步

```bat
git remote add upstream https://github.com/rathena/rathena.git
git fetch upstream
git merge upstream/master
```

冲突通常集中在 `db/re/mob_db.yml` 和 `npc` 下的汉化文件。处理原则：**结构跟上游，文本用中文**。

## 七、已知限制

- `PACKETVER 20250402` 是本源码支持的最高版本；使用更新的客户端时需要同步升级源码并调整该宏；
- 241 条怪物名称、部分新增 NPC 仍是英文；
- 本仓库不含客户端资源，客户端汉化请配合单独的 translation 工程使用。

## 八、致谢与许可

- 服务端：[rAthena](https://github.com/rathena/rathena)
- 中文文本来源：国服/台服客户端数据与自行整理，详见各文件历史；
- 许可：与上游一致，GPLv3（见 `LICENSE`）。
