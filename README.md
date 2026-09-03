# NFA for C-Style Comments

**Shanine Claire A. Besto**
**3 BSCS-A**
**CS 13a — Automata Theory and Formal Language**

A C implementation of a nondeterministic finite automaton that recognizes a single C-style comment. The alphabet is `{s, b, *, /}`, where `s` and `b` are ordinary characters — that is, anything that is not `*` or `/`.

The machine reads the opening delimiter `/*`, then the comment body, then the closing delimiter `*/`. Every move that isn't listed in the transition table leads to a dedicated trap state `qtrap`, so the automaton never gets stuck — an invalid string just drains into the trap and stays there.

## Diagram

The diagram shows five "working" states `q0 → q1 → q2 → q3 → q4` in a left-to-right chain, each connected by the symbol that advances it (`/`, `*`, `*`, `/`). `q2` and `q3` also have self-loops for the characters that don't advance the match, and a curved edge from `q3` back to `q2` for when a run of stars is broken by an ordinary character. Every state also has a transition into `qtrap` (shown as dashed red arrows) for any symbol not already accounted for.

![State Diagram](state_diagram.png)

## States

| State | Meaning |
|-------|---------|
| q0 | start state; expecting the opening `/` |
| q1 | opening `/` has been read; expecting `*` |
| q2 | opening delimiter done; inside the comment body |
| q3 | body, inside a run of `*` (possible closing delimiter starting) |
| q4 | accepting state — the closing `*/` has just been read |
| qtrap | trap state; any invalid move lands here permanently |

## Formal Definition

```
M = (Q, Σ, δ, q0, F)

Q  = { q0, q1, q2, q3, q4, qtrap }
Σ  = { s, b, *, / }
q0 = q0
F  = { q4 }
δ  : Q × Σ → Q
```

## Transition Table

| δ | s | b | * | / |
|---|---|---|---|---|
| → q0 | qtrap | qtrap | qtrap | q1 |
| q1 | qtrap | qtrap | q2 | qtrap |
| q2 | q2 | q2 | q3 | q2 |
| q3 | q2 | q2 | q3 | q4 |
| * q4 | qtrap | qtrap | qtrap | qtrap |
| qtrap | qtrap | qtrap | qtrap | qtrap |

`→` marks the start state and `*` marks the accepting state.

## δ Equations

```
δ(q0,s)=qtrap      δ(q0,b)=qtrap      δ(q0,*)=qtrap      δ(q0,/)=q1
δ(q1,s)=qtrap      δ(q1,b)=qtrap      δ(q1,*)=q2         δ(q1,/)=qtrap
δ(q2,s)=q2         δ(q2,b)=q2         δ(q2,*)=q3         δ(q2,/)=q2
δ(q3,s)=q2         δ(q3,b)=q2         δ(q3,*)=q3         δ(q3,/)=q4
δ(q4,s)=qtrap      δ(q4,b)=qtrap      δ(q4,*)=qtrap      δ(q4,/)=qtrap
δ(qtrap,s)=qtrap   δ(qtrap,b)=qtrap   δ(qtrap,*)=qtrap   δ(qtrap,/)=qtrap
```

## Sample Strings

**Accepted:** `/*s*/`  `/*b*/`  `/**/`  `/***/`  `/*sbs*bsb*/`  `/*s/b*/`

![Sample](acceptedsample.png)

**Rejected:** `/**`  `/**/s/*bb*/`  `sbs/**/bs`  `/*/`  `/**b/`  `//sbsb`

![Sample](rejectedsample.png)

## Handwritten

![Handwritten Work](handwritten.png)
