# Mini-Git Project Plan
**Course:** Data Structures – Midterm Project  
**Team:** 2 members  
**Duration:** 14 days (starting 20 November 2026)  
**Language:** C++  
**Repository:** https://github.com/momin-chezgi/minigit  

## 1. Guiding Principles
- Primary evaluation focus: understanding of data structures, ADTs, objects, workflows, and functions.
- Module ownership is clear. Deep knowledge of the other member’s internal implementation is **not** required.
- Visible boundaries between modules must be maintained through clean interfaces and directory structure.
- Work must remain flexible due to differing weekly schedules.
- AI may be used to accelerate development, but every committed piece of code must be understood and owned by a team member.
- Feature branches will be used for parallel and attributable work.

## 2. Module Ownership

**Member A (stronger C++ background)**  
- Commit linked-list model and Branch references  
- Persistence / serialization layer  
- Checkout and history traversal  
- Integration of the command dispatcher  

**Member B**  
- Staging Area (Queue) integration with the file system  
- Stash and Undo (Stack-based)  
- Sorting-related commands (`branch`, `log --date-order`, `ls-files --sort=size`)  
- Unit tests for owned modules and basic CLI argument parsing  
- Documentation structure  

Shared thin layer: simple command dispatcher that only calls the public interfaces of the owned modules.

## 3. Branching Strategy
- `main` remains the stable integration branch.
- Create a new short-lived branch for each feature or coherent set of features (e.g. `feature/commit-list`, `feature/staging-area`, `feature/persistence`).
- Prefer small, focused branches that live 1–3 days.
- Merge only completed and tested work into `main`.

## 4. Timeline (Flexible Windows)

| Phase | Window       | Goal                                      |
|-------|--------------|-------------------------------------------|
| 0     | Days 1–2     | Architecture & public interfaces locked   |
| 1     | Days 2–5     | Core data model + Staging Area (in-memory)|
| 2     | Days 5–8     | Persistence layer working                 |
| 3     | Days 7–11    | All mandatory CLI commands functional     |
| 4     | Days 11–14   | Integration, documentation, defence prep  |

Windows intentionally overlap so the member with more available time can pull work forward.

## 5. Definition of Done (for every task)
- Code written and compiling
- Unit tests passing for the owned module
- Public interface documented
- Brief note added to the architecture document if the interface changed
- Successful local demonstration of the feature

## 6. Communication & Flexibility
- Progress updates via GitHub issues or a short shared note (asynchronous).
- One optional short sync window per week (two alternative time slots will be agreed).
- If one member is unavailable, the other continues on independent modules.
- Blocked tasks are clearly marked so the other person can take alternative work.

## 7. Immediate Next Actions (Next 48 Hours)
1. Both members confirm the ownership split above.
2. Write a short architecture note defining the public interfaces between modules.
3. Create the initial set of GitHub issues with acceptance criteria.
4. Open the first feature branch(es) and begin Phase 0 / early Phase 1 work.

## 8. Stretch Goals (Only after MVP is complete)
- Delta storage
- Merge (DAG)
- `.minigitignore` + binary search
- Garbage collection (`minigit gc`)

---

**Status:** 
Member A agreed 
Still member B acception
