# Everland (Misc 250)

The challenge provides a source file [everland_19f72e788727d36b0200b0d9507aeb3f.sml](everland_19f72e788727d36b0200b0d9507aeb3f.sml)
and a host `everland.pwni.ng:7772` where the code is running.

Analyzing the code we see that we have a hero and 10 enemies,
they have some health points, strength points, and a set of actions they can execute.
The hero also has a bag with some items.
Some additional items can be collected.
Those items can be used for HP, SP or new actions.


We have to kill them all the enemies and then,
the enemy with higher strength is posessed and we have to kill it too.
Then we get the flag. Easy peasy.

At first glance, winning the fight and getting the flag seems impossible,
but there are several flaws in the program that allow us to win.

## Use recouperate


The enemies use a simple weight function to choose the action they can execute:

```sml
(ms/ts) + 3.0*(mh/th) (* ms = my strength, ts = their strengh, mh = my hp, th = their hp *)
```

From the set of enemy actions, the most effective one is `strike`, which substracts 15HP from the hero.
Executing this continuously, the hero faces a certain death.  
The good news? `(ms/ts)` gets `inf` when `ts = 0` and maximizes the weight,
so once the hero gets 0 strength the first action will be executed, not matter which one is.

This is great, since the first action is `lunge`:

```sml
their_h := 2*(!their_h) div 3; my_h := max(!my_h-10, 0)
```

So, this action will get us killed rather slowly but eventually will kill the enemy itself, nice.
The hero just need to `recouperate` themselves to avoid a certain death:

```sml
my_s := max(!my_s - 20, 0); my_h := (!my_h + 10)
```

This action reduces hero strengh and increases their health, so it fulfills both objectives.

This allows the hero to survive till the posessed enemy.

## Capture and sacrifice

The previous flaw allows the hero to survive till the final enemy, which has a single action, `kill`:

```sml
(* It kills you. You're dead *)
their_h := 0
```

It seems pretty straigthforward, but again, there's a flaw.

The enemies execute their action before the hero in a fight round,
but with the last enemy, the posession itself takes a round.
This means that the hero has a single attack it can use.

Additionally, there's an object called _Sacrifical Net_ that,
when used by the hero, gives them the ability to `capture` an enemy.

When an enemy is captured, we gain an action called `sacrifice`:

```sml
my_h := min((!my_h)+min(!e_h, !my_s*10), player_max);
e_h  := (!e_h-(!my_h)*10);
```

So we just need to have enough health and strength when sacrifying to kill the posessed enemy.

## Get the flag

We connect to the server and follow the previous steps
(`capture`,  then `recouperate` till the last enemy, then `sacrifice`)
and eventually get the flag: `PCTF{just_be_glad_i_didnt_arm_cpt_hook_with_GADTs}`
