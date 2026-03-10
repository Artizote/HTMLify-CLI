# ShortLink Subcommand Style

## URL shortning example

```
$ htmlify shortlink url1 url2
■ ShortLink
├┬ url1
│╰▶ short_url1
╰┬ url2
 ╰▶ short_url2
```

## Lookup by ID example

```
$ htmlify shortlink --id 324 789
■ ShortLink
├┬ 324
│╰▶ short_url1
╰┬ 789
 ╰▶ short_url2
```

## Lookup by shorts example

```
$ htmlify shortlink --short abcd efgh
■ ShortLink
├┬ abcd
│╰▶ short_url1
╰┬ efgh
 ╰▶ short_url2
```

