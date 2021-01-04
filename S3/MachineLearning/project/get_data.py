# TODO: zmiana tokenow zamiast time.sleep, BANY jako feature?, zmiana rangi lub dodanie playerow jak za malo meczy

import requests
import time
import random
import csv

summoner_names = ['maksimus86', 'siarka071200', 'StaryAdama', 'SynStaregoAdama', 'Siur3k', 'Onnax', 'latarniakonto']

def next_division(division):
    if division == 'I':
        return 'II'
    if division == 'II':
        return 'III'
    if division == 'III':
        return 'IV'

class RiotApi():

    def __init__(self, riot_token, region):
        self.solo_ids = {'IRON': [], 'BRONZE': [] , 'SILVER' : [], 'GOLD' : [], 
        'PLATINUM' : [], 'DIAMOND': [], 'MASTER': [], 'GRANDMASTER' : [], 'CHALLENGER': []}
        self.flex_ids = {'IRON': [], 'BRONZE': [] , 'SILVER' : [], 'GOLD' : [], 
        'PLATINUM' : [], 'DIAMOND': [], 'MASTER': [], 'GRANDMASTER' : [], 'CHALLENGER': []}
        self.token_id = 0
        self.tokens = [riot_token]
        self.region = region
        self.season = 13

    def send_request(self, URL):
        HEADERS = {
            "Accept-Language": "en-US,en;q=0.5",
            "Accept-Charset": "application/x-www-form-urlencoded; charset=UTF-8",
            "Origin": "https://developer.riotgames.com",
            "X-Riot-Token": self.tokens[self.token_id]
        }
        try:
            r = requests.get(url = URL, headers = HEADERS)
        except Exception as err:
            print('[-] Error occurred: {err}')
            return None

        first = self.token_id
        self.token_id = (self.token_id + 1) % len(self.tokens)
        flag = False
        while 'Retry-After' in r.headers: # Rate limi exceeded
            flag = True
            if self.token_id == first: # we tried all tokens
                wait_time = int(r.headers['Retry-After'])
                print('[-] Rate limit exceeded on all tokens, time.sleep for {} seconds...'.format(wait_time))
                time.sleep(wait_time)
            else:
                print('[-] Rate limit exceeded, changing token.\n')
                self.token_id = (self.token_id + 1) % len(self.tokens)
                HEADERS['X-Riot-Token'] = self.tokens[self.token_id]
            try:
                r = requests.get(url = URL, headers = HEADERS)
            except Exception as err:
                print('[-] Error occurred: {err}')
                return None
        if flag:
            print('[+] Successfuly resent request.\n')
        return r

    def summ_to_acc_id(self, summoner_id):
        URL = 'https://{}.api.riotgames.com/lol/summoner/v4/summoners/{}'.format(self.region, summoner_id)
        r = self.send_request(URL)
        if r is None:
            return None
        try:
            return r.json()['accountId']
        except KeyError:
            print('URL: {}'.format(URL))
            print('CURRR TOKENID{}'.format(self.token_id))
            print(r.json())

    def get_acc_id_by_name(self, summoner_name):
        URL = 'https://{}.api.riotgames.com/lol/summoner/v4/summoners/by-name/{}'.format(self.region, summoner_name)
        r = self.send_request(URL)
        if r is None:
            return None

        return r.json()['accountId']

    def get_summoner_id_by_name(self, summoner_name):
        URL = 'https://{}.api.riotgames.com/lol/summoner/v4/summoners/by-name/{}'.format(self.region, summoner_name)
        r = self.send_request(URL)
        if r is None:
            return None

        return r.json()['id']

    def get_league(self, summoner_id):
        URL = 'https://{}.api.riotgames.com/lol/league/v4/entries/by-summoner/{}'.format(self.region, summoner_id)
        r = self.send_request()

        if r is None:
            return None, None

        solo_r, flex_r = None, None
        for d in r.json():
            if d['queueType'] == 'RANKED_SOLO_5x5':
                solo_r = d['tier']
            if d['queueType'] == 'RANKED_FLEX_SR':
                flex_r = d['tier']

        return solo_r, flex_r

    def get_match_ids(self, acc_id):
        #   420 - Ranked Solo 5v5
        #   430 - Normal Blind 5v5
        #   440 - Ranked Flex 5v5
        #   480 - Normal Draft 5v5
        URL = 'https://{}.api.riotgames.com/lol/match/v4/matchlists/by-account/{}?queue=420'.format(self.region, acc_id)
        r = self.send_request(URL)
        if r is None:
            return None

        match_list = r.json()['matches']

        solo_match_ids = [d['gameId'] for d in match_list if d['season'] == self.season and d['queue'] == 420]
        flex_match_ids = [d['gameId'] for d in match_list if d['season'] == self.season and d['queue'] == 440]

        return solo_match_ids, flex_match_ids

    def add_matches_by_name(self, summoner_name):
        acc_id = self.get_acc_id_by_name(summoner_name)
        summoner_id = self.get_summoner_id_by_name(summoner_name)

        if acc_id is None or summoner_id is None:
            return None

        return self.add_matches_from_summoner(acc_id, summoner_id)

    def add_matches_from_summoner(self, acc_id, summoner_id):
        solo_match_ids, flex_match_ids = self.get_match_ids(acc_id)
        solo_rank, flex_rank = self.get_league(summoner_id)
        self.solo_ids[solo_rank].extend(solo_match_ids)
        self.flex_ids[flex_rank].extend(flex_match_ids)

    def get_summoner_ids_by_tier(self, tier, division, max_ids = 1000, queue = 'RANKED_SOLO_5x5'):
        ids = []
        cnt = 1
        print('[+] Getting {} summoners  ID\'s from {} {}!\n'.format(max_ids, tier, division))
        while len(ids) < max_ids:
            URL = 'https://{}.api.riotgames.com/lol/league/v4/entries/{}/{}/{}?page={}'.format(self.region, queue, tier, division, cnt)
            r = self.send_request(URL)
            if r is None:
                return None

            r_list = r.json()

            tmp = [d['summonerId'] for d in r_list]
            if not tmp:
                print('[-] Can\'t get more ID\'s. Stop!\n')
                break

            ids.extend(tmp)
            cnt+=1
            print('Got {}/{} ID\'s'.format(len(ids), max_ids))

        print('\n[+] Returning {} ID\'s!\n'.format(len(ids)))
        return ids

    def add_matches_by_tier(self, tier, division = 'I', max_matches = 10000):
        high_elo = ['MASTER', 'GRANDMASTER', 'CHALLENGER']
        low_elo = ['IRON', 'BRONZE', 'SILVER', 'GOLD', 'PLATINUM', 'DIAMOND']

        if tier in high_elo: # special api for high elo leagues
            return

        print('[+] Adding new match ID\'s.\nTier: {}\nDivison:{}\n'.format(tier, division))

        if tier in low_elo:
            summ_ids = self.get_summoner_ids_by_tier(tier, division, max_matches//10)
            print('[+] Starting getting summoner\'s ID\'s from account ID\'s.\n')
            acc_ids = [self.summ_to_acc_id(Id) for Id in summ_ids]
            for acc_id in acc_ids:
                solo_ids, flex_ids = self.get_match_ids(acc_id)
                old = len(self.solo_ids[tier])
                print('{}/{}    {}%\completed'.format(old, max_matches, 100*old/max_matches))
                self.solo_ids[tier].extend(solo_ids)
                self.solo_ids[tier] = list(set(self.solo_ids[tier]))
                if len(self.solo_ids[tier]) == old:
                    if division == 'IV':
                        print('[-] Cannot add any new matches! Terminating with {} out of {} needed match ID\'s\n'.format(old, max_matches))
                        break
                    else:
                        print('[-] Cannot add any new matches! Changing division from {} to {}.\n'.format(division,next_division(division)))
                        division = next_division(division)

                if len(self.solo_ids[tier]) >= max_matches:
                    print('[+] We have all {} needed match ID\'s. Stop!'.format(max_matches))
                    break

    def get_match_data(self, match_id):
        URL = 'https://{}.api.riotgames.com/lol/match/v4/matches/{}'.format(self.region, match_id)
        r = self.send_request(URL)
        if r is None:
            return None

        response = r.json()
        match_data = {}
        try:
            if response['gameDuration'] < 600: # Remakes, not rankeds etc.
                print('[-] Remake! Skip.\n')
                return None
            if response['queueId'] != 420: 
                print('[-] Not soloQ! Skip.\n')
                return None
        except KeyError:
            print('BAD ID: {}'.format(match_id))
            return None

        try:
            participants_list = response['participants']
        except  KeyError:
            print('BAD ID: {}'.format(match_id))
            return None

        match_data['match_id'] = match_id

        try:
            match_data['1_result'] = response['teams'][0]['win'] if response['teams'][0]['teamId'] == 100 else response['teams'][1]['win']
        except  KeyError:
            print('BAD ID: {}'.format(match_id))
            return None

        for participant in participants_list:
            participant_data = self.get_player_stats(participant)
            if participant_data is None:
                return None
            prefix = participant_data['team'] + participant_data['role'] + '_'
            participant_data.pop('team')
            participant_data.pop('role')
            participant_data = {prefix+k: v for k, v in participant_data.items()}
            match_data = {**match_data, **participant_data}

        return match_data

    def get_player_stats(self, response_data):
        player_data = {}
        player_data['team'] = str(response_data['teamId']/100) # 1 or 2
        player_data['role'] = response_data['timeline']['lane']
        if player_data['role'] == 'NONE': # remake/dodge
            return None
        if player_data['role'] == 'BOTTOM' or player_data['role'] == 'BOT':
            player_data['role'] = 'ADC' if response_data['timeline']['role'] == 'DUO_CARRY' else 'SUPPORT'
        if player_data['role'] == 'MIDDLE':
            player_data['role'] == 'MID'

        player_data['championId'] = response_data['championId']
        player_data['xp_per_min'] = response_data['timeline']['xpPerMinDeltas']['0-10']
        player_data['creeps_per_min'] = response_data['timeline']['creepsPerMinDeltas']['0-10']
        player_data['gold_per_min'] = response_data['timeline']['goldPerMinDeltas']['0-10']
        player_data['damage_taken_per_min'] = response_data['timeline']['damageTakenPerMinDeltas']['0-10']
        player_data['first_blood'] = response_data['stats']['firstBloodKill']
        player_data['first_blood_assist'] = response_data['stats']['firstBloodAssist']
        player_data['first_tower'] = response_data['stats']['firstTowerKill']
        player_data['first_tower_assist'] = response_data['stats']['firstTowerAssist']

        return player_data

    def create_dataset(self, tier, queue):
        if queue == 'RANKED_SOLO_5x5':
            match_ids = self.solo_ids[tier]
        if queue == 'RANKED_FLEX_SR':
            match_ids = self.flex_ids[tier]

        file_name = self.region + '_' + tier + '_' + queue + '.csv'
        with open(file_name, 'w', newline='') as file:
            writer = csv.writer(file)
            columns_names = None
            cnt = 0
            for ID in match_ids:
                if cnt % 200 == 0:
                    print('[+] Got {}/{}!\n'.format(cnt, len(match_ids)))
                cnt+=1
                print(ID)
                match_data = self.get_match_data(ID)
                if columns_names is None and match_data is not None:
                    columns_names = [k  for  k in  match_data.keys()]
                    writer.writerow(columns_names)
                if match_data is not None: # remakes
                    writer.writerow(list(match_data.values()))
                else:
                    print('[-] Remake/bad match! Skip: {}\n'.format(ID))