# Daily Protocol

Same loop every day, whatever module I'm on. `NN` = current module number.

---

## 0 · Open the session (2 min)

```bash
cd ~/cs-study
./scripts/new-session.sh        # creates + opens log/YYYY-MM-DD.md
./scripts/status.sh             # where did I stop yesterday?
```

Fill the log header now, not later: **Topic** and the one-line goal for today.
If yesterday's module isn't finished, today is the same module. Modules take
as many days as they take.

---

## 1 · Orient (10 min)

Open `notes/NN-*/README.md` and the module's section in `README.md`.

Before any video, write one sentence in the log: **what I think this topic is
and where I'd use it.** Wrong is fine — the point is to have a prior to correct.
Then read the `Implement:` checkboxes for this module. That list is the target;
everything else today serves it.

Resources for the module are already in `notes/NN-*/README.md` under
"Available (from upstream)". Don't go hunting for better ones.

---

## 2 · Learn (45–90 min)

Watch/read. Take notes **in the log, not the notes file** — messy is fine here,
this is scratch.

Rules:
- Pause and predict before any worked example. Guess the answer, then check.
- Two resources maximum per concept. A third means you're avoiding step 4.
- Anything you don't understand goes in `## 6. Open questions` in the notes
  file immediately. Don't let it slide.

---

## 3 · Close every tab

Non-negotiable. Everything below happens with the material shut.

---

## 4 · Write the notes (20–30 min)

Fill `notes/NN-*/README.md` from memory:

| Section | What goes in it |
|---|---|
| 1. Core idea | One paragraph, plain language, no jargon you can't unpack |
| 2. Mechanism | How it actually works. ASCII diagram if it's structural |
| 3. Complexity | Fill the table. Derive it, don't recall it |
| 4. Implementation notes | Leave empty until step 5 |
| 5. When would I reach for this | Tie to real work where honest — planners, buffers, graph search |
| 6. Open questions | Anything still fuzzy |

If a section won't come, you haven't learned it. Reopen the resource for that
one thing, close it, try again.

**Commit:**
```bash
git add -A && git commit -m "NN-topic: notes on <concept>"
```

---

## 5 · Implement (60–120 min) — the part that counts

Work the module's `Implement:` list top to bottom, in `src/cpp/NN-*/` and
`src/python/NN-*/`.

- **From scratch.** No standard-library version of the thing you're building.
- **C++ first** when the topic is structural (memory, pointers, layout).
  **Python first** when it's algorithmic (recursion, DP, graph logic).
  Then port to the other. The port is where gaps surface.
- Run tests as you go:
```bash
make test-cpp
make test-py
make test
```

**Stuck rule:** 25 minutes on one bug before looking anything up. Then look up
*the specific concept*, never a full implementation. If you read someone's
solution, delete your file and rewrite it from scratch the next day.

Every gotcha, off-by-one and edge case goes into `## 4. Implementation notes`
as you hit it. That section is the highest-value part of the whole notes file
in six months.

**Commit per working piece, not per day:**
```bash
git add -A && git commit -m "NN-topic: implement <method> in C++"
```

---

## 6 · Apply (45–60 min)

2–3 LeetCode problems tagged to this module, into `problems/NN-*/`. Easy →
easy → medium.

Per problem, before writing code:
1. Restate it in your own words in the log.
2. State the approach and its complexity **out loud**.
3. Then code.

Write it up from `problems/TEMPLATE.md` into `problems/NN-*/`.

**Stuck rule:** 45 minutes, then read the editorial — and log the problem for
re-solve from scratch in three days. A problem you read the answer to is not
solved. Any problem where you read the editorial gets a row in
`reference/resolve-queue.md`, re-solved from scratch three days later.

Fill the log's problem table: number, name, verdict, approach, complexity.

**Commit:**
```bash
git add -A && git commit -m "NN-topic: solve <problem names>"
```

---

## 7 · Make cards (5 min)

2–5 Anki cards from **your own notes**, never from the source material.
Good: "worst case of quicksort and why", "which sorts are stable", "space
complexity of DFS on a tree". Bad: anything you'd have to recite verbatim.

---

## 8 · Close the session (5 min)

In the log, fill:
- **What I got wrong** — the honest one. Bugs, wrong complexity guesses,
  misunderstood mechanisms. This section is why the log exists.
- **Tomorrow** — the next concrete action, not "continue arrays".

Then tick boxes in `README.md`. **A box gets ticked only when:** implemented
from scratch, tests pass, 2–3 problems solved on it. Not when the video ended.

```bash
./scripts/progress.sh
git add -A
git commit -m "NN-topic: session log + progress"
git push
```

---

## Module done checklist

Before moving to `NN+1`:

- [ ] Every `Implement:` box in this module's README section is ticked
- [ ] Both C++ and Python versions exist and pass tests
- [ ] Notes sections 1–5 complete; section 6 empty or answered
- [ ] 2–3 problems in `problems/NN-*/`
- [ ] Complexity table derived from scratch, not recalled
- [ ] Status line in the notes file updated to `complete` with the date
- [ ] Anki cards made

Then update the notes header dates and commit:
```bash
git add -A && git commit -m "NN-topic: module complete"
git push
```

---

## Weekly (pick a fixed day)

```bash
./scripts/progress.sh
./scripts/status.sh
git log --oneline --since="1 week ago"
```

- Re-solve one problem you needed the editorial for, from scratch
- Re-implement one structure from a previous module, from scratch, no notes
- Anki review of everything so far
- Read back the "What I got wrong" lines from the week — the repeats are your
  real weak spots

---

## Commit message format

```
NN-topic: <what changed>
02-arrays: notes on dynamic resizing and amortized cost
02-arrays: implement push/pop/resize in C++
02-arrays: port vector to Python
02-arrays: solve 27, 88, 1089
02-arrays: module complete
```

Several small commits per day. `git log` should read as a study history.

---

## When a day goes wrong

- **Under an hour available:** step 6 only — one problem on the current module. Commit it.
- **Nothing works, everything's confusing:** stop. Log what confused you and push. Come back tomorrow. Grinding a wall you don't understand teaches nothing.
- **Missed days:** don't backfill, don't "catch up". Open the last log, read Tomorrow, start there.

---

## The three rules everything else serves

1. **Learn and apply in the same session.** Never batch videos now and problems later — that's the mistake the whole upstream repo warns about.
2. **Write it from memory or you don't know it.** Notes with the tab open are transcription, not learning.
3. **The checkbox lies if the code doesn't exist.** The repo is the evidence; the checklist is only an index over it.
